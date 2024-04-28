#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <iostream>

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
 private:
  AMateria* _materia[4];

 public:
  MateriaSource();
  MateriaSource(MateriaSource const& rhs);
  virtual ~MateriaSource();

  MateriaSource& operator=(MateriaSource const& rhs);

  virtual void learnMateria(AMateria* materia);
  virtual AMateria* createMateria(std::string const& type);
};

#endif
