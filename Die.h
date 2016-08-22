#ifndef DIE_H
#define DIE_H

#include <random>

//class to simulate a die
//note that the RNG must be seeded via the seed function (just once per program as it is static) or the default std::mt19937 seed will be used
class Die
{
	 public:
		//call with the number of sides the die should have
		explicit Die(unsigned int _sides=6);
		~Die()=default;
		
		//roll the dice and return the result
		unsigned int roll();
		//return the current value of the dice
		unsigned int getValue() const;
		
		// function to seed the RNG
		static void seed(unsigned int _seed);
		
	private:
		//number of sides
		const unsigned int sides;
		//initial value is set to 1
		unsigned int current_value;
		
		//the distribution the dice uses to generate random numbers
		std::uniform_int_distribution<double> distribution;
		//mersenne twister PRNG
		static std::mt19937 twister;
};

#endif
