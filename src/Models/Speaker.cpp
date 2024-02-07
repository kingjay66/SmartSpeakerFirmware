#include <Models/Speaker.hpp>
#include <string>
#include <utility>

Speaker::Speaker()
  : id("NOID")
  , name("NONAME") {
}

Speaker::Speaker(std::string id, std::string name)
  : id(std::move(id))
  , name(std::move(name)) {
}
