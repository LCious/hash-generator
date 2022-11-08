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

## Test analysis:

- File containing only `a`

    ### Input:
    
    ```console
  a
    ```
    
    ### Output:
    
    ```console
    4669A0669B90588D699E5F949A957766A0B1AA67A1728470A2A19DB4AAB1AAB9
    
    4669A0669B90588D699E5F949A957766A0B1AA67A1728470A2A19DB4AAB1AAB9
    ```
   
- File containing only `b`

    ### Input:
    
    ```console
  b
    ```
    
    ### Output:
    
    ```console
    466CA3699E8F5B8E669D62939B947A69A3B2A964A07581719FA09CB1ABB0ADBC
    
    466CA3699E8F5B8E669D62939B947A69A3B2A964A07581719FA09CB1ABB0ADBC
    ```
 - File containing nothing (empty file)

    ### Input:
    
    ```console
  
    ```
    
    ### Output:
    
    ```console
    45887E83776B72647F7575696C688977707E78726D7D8C77686863776C746C7A
    
    45887E83776B72647F7575696C688977707E78726D7D8C77686863776C746C7A
    ```
  - First file containing random text (1500 symbols)
    
    ### Output:
    
    ```console
    DF2C12372B1B26283F35393930385D5B445258625D717C7B686863878084709E
    
    DF2C12372B1B26283F35393930385D5B445258625D717C7B686863878084709E
    ```
  - Second file containing random text (1500 symbols)
    
    ### Output:
    
    ```console
    DF17252A3E26193D2C482444454B484657676B57685C69687D7B769C8D9783A9
    
    DF17252A3E26193D2C482444454B484657676B57685C69687D7B769C8D9783A9
    ```
  - Files containing different words in middle 'lorem lorem lorem' and 'LOREM LOREM LOREM'
    
    ### Input:
    ```console
    Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s,  when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.Lorem Ipsum is lorem lorem lorem dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
    ```
    ```console
     Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.Lorem Ipsum is LOREM LOREM LOREM dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
    ```
    ### Output:
    ```console
    9BC8EFC5FAEBB71CF429EE1F192006254F6065225C313F5F8D8C889F999C89D8
    
    AAB71EB4291AA64BE358DD4E484FF5349EAFB431AB404E6EDCDBD7EEE8EBD847
    ```  

   
