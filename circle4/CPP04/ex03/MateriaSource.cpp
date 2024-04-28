#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : _materia() {}

MateriaSource::MateriaSource(MateriaSource const& object) { *this = object; }

MateriaSource::~MateriaSource() {
  for (int i = 0; i < 4; i++) {
    delete _materia[i];
    _materia[i] = NULL;
  }
}

MateriaSource& MateriaSource::operator=(MateriaSource const& object) {
  if (this != &object) {
    for (int i = 0; i < 4; i++) {
      delete _materia[i];
      _materia[i] = object._materia[i]->clone();
    }
  }

  return *this;
}

void MateriaSource::learnMateria(AMateria* m) {
  if (m == NULL) {
    std::cout << "Materia is NULL" << std::endl;
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (_materia[i] == NULL) {
      _materia[i] = m;
      break;
    }
  }
}

AMateria* MateriaSource::createMateria(std::string const& type) {
  for (int i = 0; i < 4; i++) {
    if (_materia[i] != NULL && _materia[i]->getType() == type) {
      return _materia[i]->clone();
    }
  }

  return NULL;
}
