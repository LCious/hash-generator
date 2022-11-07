# A github repository for the Block-chain course

# Simplified hash generator

## Apie hash funkciją
Hash funkcija atitinka šiuos reikalavimus:

* Hash funkcijos įėjimas (angl. input) gali būti bet kokio dydžio simbolių eilutė (angl. string).
* Hash funkcijos išėjimas (angl. output) visuomet yra to paties, fiksuoto, dydžio rezultatas (64 simbolių hex'as).
* Hash funkcija yra deterministinė.
* Hash funkcijos reikšmė/kodas (hash‘as) bet kokiai input'o reikšmei yra apskaičiuojamas greitai - efektyviai.
* Iš hash funkcijos rezultato (output'o) praktiškai neįmanoma atgaminti pradinio įvedimo (input'o).
* Hash funkcija yra atspari "kolizijai" (angl. collision resistance).

## Hash funkcijos veikimo principas
Algoritmas turi pradinį seed'ą, su kuriuo yra modifikuojamas pradinio įvedimo simbolių eilutė ją pasivertus į `int` tipą. Gavus initial_hash, jis yra paverčiamas į `string`, kuriame yra apskaičiuojamas gautojo initial_hash size. Susikūrus papildomą random_variable yra vykdoma galutinė hash funkcija, kuri išveda hex 64 simbolių eilutę.

## Programos įdiegimas ir naudojimasis 
* Atsisiųskite vieną programos versijų iš [Releases](https://github.com/LCious/hash-generator/releases) aplanko ir ją išarchyvuokite.
* Atsisiųskite jums patinkančią __C++__ palaikančią programą (_[Visual Studio](https://visualstudio.microsoft.com/downloads/), [CodeBlocks](https://www.codeblocks.org/downloads/)_).
* Atsidarykite pateiktą programos kodą ir jį paleiskite arba komandinėje eiltuėje įrašykite `g++ -o main *.cpp` ir paleiskite su `./main`

## Hash
```c++
	Hash(){
		for (int i = 1; i < 64; i++){
			for (int j = 0; j < s.size(); j++){
				temp = hash[i];
				temp = temp ^ int(s[j]);
				hash[i] = char(temp);
				hash[i - 1] += i ^ j;
			}
			hash[i] = int(hash[i]) + int(hash[64 - i]);
		}
		auto end = std::chrono::steady_clock::now();

		hash = string_to_hex(hash);
		hash.resize(64);
	}
```

