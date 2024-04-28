#include "Serializer.hpp"

int main() {
  Data data;
  data.name = "Sungwook";
  data.level = 42;

  uintptr_t serialized = Serializer::serialize(&data);
  std::cout << "Serialized: " << serialized << std::endl;

  Data *deserialized = Serializer::deserialize(serialized);

  std::cout << "Deserialized name: " << deserialized->name << std::endl;
  std::cout << "Deserialized level: " << deserialized->level << std::endl;

  return 0;
}