#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml.h"

struct Object {
  int GetPropertyInt(const std::string &getName);
  float GetPropertyFloat(const std::string &getName);
  std::string GetPropertyString(const std::string &getName);
  std::string name;
  std::string type;
  sf::Rect<float> rect;
  std::map<std::string, std::string> properties;
  sf::Sprite sprite;
};

struct Layer {
  int opacity;
  std::vector<sf::Sprite> tiles;
};

class Level {
 public:
  bool LoadFromFile(const std::string &filename);
  Object GetObject(const std::string &name);
  std::vector<Object> GetObjects(const std::string &name);
  std::vector<Object> GetAllObjects();
  void Draw(sf::RenderWindow &window);
  sf::Vector2i GetTileSize() const;

 private:
  int width, height, tileWidth, tileHeight;
  int firstTileID;
  sf::Rect<float> drawingBounds;
  sf::Texture tilesetImage;
  std::vector<Object> objects;
  std::vector<Layer> layers;
};
