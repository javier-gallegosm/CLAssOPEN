#include <omp.h>
#include <algorithm>
#include <iostream>
#include <random>

/**
 * @param inferior valor mínimo posible a buscar aleatoreamente
 * @param superior valor máximo a buscar aleatoreamente
 * @return regresa un valor aleatoreo entre los límites (inclusive)
 */
int aleatoreo(int inferior, int superior);

/**
 * @param largo tamaño del token
 * @return Regresa una cadena de caracteres aleatorea especificada por el largo
 */
std::string getToken(int largo);

int main(int argc, char** argv) {
  std::cout << std::endl;

  int largo = aleatoreo(13, 333);
  std::cout << std::endl << getToken(largo) << std::endl;

  return 0;
}

int aleatoreo(int inferior, int superior) {
  std::random_device dispositivo;
  std::uniform_int_distribution<int> distribucion(inferior, superior);
  return distribucion(dispositivo);
}

std::string getToken(int largo) {
  static const char letras[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

  char* texto = new char[largo];
#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < largo; i++) {
      texto[i] = letras[aleatoreo(0, sizeof(letras) - 1)];
    }
  }
  std::string token = std::string(texto);
  delete texto;

  return token;
}
