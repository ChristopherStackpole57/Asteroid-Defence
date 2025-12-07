// Christopher Stackpole, 12/06/2025

#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "ServiceInterface.h"

// Forward declaration for CallService to avoid circular dependencies
// Execution logic needs to be deferred to CallService, which is why we have to directly communicate with it.
class CallService;

class ServiceManager
{
public:
	// Templated service registering to ensure type-safety (compile time safety, specifically)
	template<typename T>
	T* RegisterService()
	{
		// We must ensure the requested service for registry actually derives from the service interface
		static_assert(std::is_base_of<IService, T>::value, "ServiceManager: Attempted to register service not deriving from IService");
	
		// Create an instance of the relevant service
		auto service = std::make_unique<T>();
		T* service_pointer = service.get();

		// With service created, register it
		// std::move used as services are large, so it would be computationally expensive to manipulate them holistically
		registered_services[typeid(T)] = std::move(service);

		// Return pointer to user
		return service_pointer;
	}

	template<typename T>
	T* Get()
	{
		// Very simple operation, simply return the service registered in the hash map at the type info of the requested type
		// Look for service index in hash map, using auto to simplify interacting with iterator indices
		auto service_index = registered_services.find(typeid(T));
		
		// Ensure find did not return invalid (end) index
		if (service_index != registered_services.end())
		{
			return static_cast<T*>(service_index->second.get());
		}

		// Otherwise the service does not exist, and we should return a nullptr
		return nullptr;
	}

	void Start();
	void Shutdown();
	void Tick(float dt);
private:
	// Storing the services in a hash map to ensure the stability of a Singleton pattern for the services
	std::unordered_map<std::type_index, std::unique_ptr<IService>> registered_services;
};

// Instantiate a singleton for use across the project
inline ServiceManager& Services()
{
	static ServiceManager service_manager;
	return service_manager;
}

#endif