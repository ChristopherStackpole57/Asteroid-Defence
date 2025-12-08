using header only definitions because of template restrictions
putting wrappers around SFML resource logic (sf::Texture, sf::Image, etc., to hide the underlying logic from game code)

optimization ideas:
- call order always tracks set of priorities, updated when object added or removed from set