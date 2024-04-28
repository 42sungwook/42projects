#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target){};

ShrubberyCreationForm::~ShrubberyCreationForm(){};

void ShrubberyCreationForm::action(Bureaucrat const &executor) const {
  AForm::execute(executor);
  std::ofstream file;
  file.open(this->_target + "_shrubbery");
  if (!file.is_open()) {
    std::cout << "Error: file open failed" << std::endl;
    return;
  }
  std::cout << "ASCII tree created: " << this->_target << "_shrubbery"
            << std::endl;
  file << "                                                      .\n"
          "                                              .         ;\n"
          "                 .              .              ;%     ;;\n"
          "                   ,           ,                :;%  %;\n"
          "                    :         ;                   :;%;'     .,\n"
          "           ,.        %;     %;            ;        %;'    ,;\n"
          "             ;       ;%;  %%;        ,     %;    ;%;    ,%'\n"
          "              %;       %;%;      ,  ;       %;  ;%;   ,%;'\n"
          "               ;%;      %;        ;%;        % ;%;  ,%;'\n"
          "                `%;.     ;%;     %;'         `;%%;.%;'\n"
          "                 `:;%.    ;%%. %@;        %; ;@%;%'\n"
          "                    `:%;.  :;bd%;          %;@%;'\n"
          "                      `@%:.  :;%.         ;@@%;'\n"
          "                        `@%.  `;@%.      ;@@%;\n"
          "                          `@%%. `@%%    ;@@%;\n"
          "                            ;@%. :@%%  %@@%;\n"
          "                              %@bd%%%bd%%:;\n"
          "                                #@%%%%%:;;\n"
          "                                %@@%%%::;\n"
          "                                %@@@%(o);  . '\n"
          "                                %@@@o%;:(.,'\n"
          "                            `.. %@@@o%::;\n"
          "                               `)@@@o%::;\n"
          "                                %@@(o)::;\n"
          "                               .%@@@@%::;\n"
          "                               ;%@@@@%::;.\n"
          "                              ;%@@@@%%:;;;.\n"
          "                          ...;%@@@@@%%:;;;;,.."
       << std::endl;
  file.close();
}
