/**
 * \file test_rosenbrock_simplex.cpp
 */

#include <iostream>
#include "Eigen/Core"

#include "simplex.h"
#include "criteria.h"

typedef Eigen::Vector2f ContainerRosenbrock;

// Fonction de coût classique
struct Rosenbrock
{
  float operator()(const ContainerRosenbrock& parameters) const
  {
    return (parameters(1, 0) - parameters(0, 0) * parameters(0, 0)) * (parameters(1, 0) - parameters(0, 0) * parameters(0, 0))
        + (1 - parameters(0, 0)) * (1 - parameters(0, 0));
  }
};

int main(int argc, char** argv)
{
  ContainerRosenbrock start_point;
  start_point << 10, 10;

  Rosenbrock fun;

  long max_iterations = 1000;
  float ftol = 0.00001;

  auto optimizer = Optimization::Local::build_simplex( // Builder pour générer automatiquement le bon type d'optimiseur
      fun(start_point),                                // indication du type de valeur de retour de la fonction
      start_point,                                     // indication du type des paramètres qui seront utilisés
      fun,                                             // indication du type de fonction qui sera passée en paramètre
      Optimization::Local::make_and_criteria(Optimization::Local::IterationCriterion(max_iterations),
          Optimization::Local::RelativeValueCriterion<float>(ftol))); // Critère d'arrêt composite

  optimizer.set_start_point(start_point);  // Valeur de départ
  optimizer.set_delta(1);                  // Taille du polytope
  optimizer.optimize(fun);                 // Optimisation de la fonction

  std::cout << "Starting point: " << start_point << std::endl;
  std::cout << "Starting value: " << fun(start_point) << std::endl;
  std::cout << "Best point: " << optimizer.get_best_parameters() << std::endl; // Récupération des meilleurs paramètres
  std::cout << "Best value: " << optimizer.get_best_value() << std::endl;      // Récupération de la meilleure valeur
}

