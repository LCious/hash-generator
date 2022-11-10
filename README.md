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
Algoritmas turi pradinį seed'ą, su kuriuo yra modifikuojamas pradinio įvedimo simbolių eilutė ją pasivertus į `int` tipą. Pabaigus suktis algoritmui gauname initial_hash, kuris yra simbolių kratinys, funkcijos `string_to_hex` pagalba yra verčiamas į simbolius kurių mums reikia `0123456789ABCDEF`. Tačiau hash'as gaunasi per ilgas, todėl susitvarkome iki tinkamo ilgio.

## Programos įdiegimas ir naudojimasis 
* Atsisiųskite vieną programos versijų iš [Releases](https://github.com/LCious/hash-generator/releases) aplanko ir ją išarchyvuokite.
* Atsisiųskite jums patinkančią __C++__ palaikančią programą (_[Visual Studio](https://visualstudio.microsoft.com/downloads/), [CodeBlocks](https://www.codeblocks.org/downloads/)_).
* Atsidarykite pateiktą programos kodą ir jį paleiskite arba komandinėje eiltuėje įrašykite `g++ -o main *.cpp` ir paleiskite su `./main`

## Programos veikimas
Atsidarius programą, naudotojas gali rinktis iš jam duotų 5 variantų:
1. Input in console
2. Input from file
3. Comparison
4. Generate files
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
		hash = string_to_hex(hash);
		hash.resize(64);
	}
```
# TESTS
## Test analysis:
- Simillar text

    ### Input:
    
    ```console
    vilnius
    
    Vilnius
    
    Vilnius!
    ```
    
    ### Output:
    
    ```console
    5A779281A49684B5D8BEC9B6B9C3CA02E6F910FF17F10632213F354D37464181
    
    5A57B261C4766495F89EA99699A3EA22C6D930DF37D12612015F156D576661A1
    
    607D9583A59883C5E7CCD4C2C4CBD31AFD0D2311280317523E5D5267506058A7
    ```
- File containing only `a`

    ### Input:
    
    ```console
  a
    ```
    
    ### Output:
    
    ```console
    45558A5D9C705C63A6687164676B989C6475A87BAF6BA4806DA983B59FB4A9B9
    
    45558A5D9C705C63A6687164676B989C6475A87BAF6BA4806DA983B59FB4A9B9
    ```
   
- File containing only `b`

    ### Input:
    
    ```console
  b
    ```
    
    ### Output:
    
    ```console
    45528D5C9F715F60A3697461646E959D6174AB7AB26CA17D6CAA80B8A2B1ACBC
    
    45528D5C9F715F60A3697461646E959D6174AB7AB26CA17D6CAA80B8A2B1ACBC
    ```
 - File containing nothing (empty file)

    ### Input:
    
    ```console
  
    ```
    
    ### Output:
    
    ```console
    4472687A7889767A7C7D8777797E686B728476887B746C87756E877A63756B7A
    
    4472687A7889767A7C7D8777797E686B728476887B746C87756E877A63756B7A
    ```
  - First file containing random text (1500 symbols)
    
    ### Output:
    
    ```console
    DE120C2A2C3D2A3A3C414B474952383F52645A786F685C877562877E77856F8E
    
    DE120C2A2C3D2A3A3C414B474952383F52645A786F685C877562877E77856F8E
    ```
  - Second file containing random text (1500 symbols)
    
    ### Output:
    
    ```console
    DE071F1D372A1D2F492E3E34363D4D5447576D6B7A55697C687774918A9A82A1
    
    DE071F1D372A1D2F492E3E34363D4D5447576D6B7A55697C687774918A9A82A1
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
    9AB0E9B8FBCFBBEE31F700EFF2FA234B1F3067366E2A5F6B58886E948E9F88C8
    
    A99F18A72ABEAADD60E6EFDEE1E9529A2E3FB645BD39AE7A67D77DE3DDEED737
    ```  
## Speed testing (konstitucija.txt) 
### Hashing speed comparison
   
Lines      |   2     |  4      |  8      |  16       |  32       |  64       |  128      |  256      |  512      |  789      |
-----------|---------|---------|---------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
Speed      | 0,000016s | 0,00005s|  0,00010s | 0,00032s  | 0,00045s | 0.00097 s  | 0.00214 s | 0.00362 s| 0.00794 s | 0.01423 s |

## Collision testing
- Test with 100 000 randomly generated lines - 1000 each
Output:
```console
Eiluciu skaicius: 100000
Koliziju skaicius: 0
```
- Test with 50 000 randomly generated pairs of lines with 1 different symbol
Output:
```console
Eiluciu skaicius: 100000
Koliziju skaicius: 0
```
## Avalanche effect testing
To hash 50 000 pairs of rows
<br>**Minimum, Average, Maximum** HEXADECIMAL similarities were:
```console
----------HEXADECIMAL SIMILARITIES-----------
minimum similarity: 20.3125%
average similarity: 50.7625%
maximum similarity: 73.4375%
---------------------------------------------
```
**Minimum, Average, Maximum** BINARY similarities were:
```console
 ------------BINARY SIMILARITIES-------------
 minimum similarity: 54.2969%
 average similarity: 70.8375%
 maximum similarity: 87.1094%
 ---------------------------------------------
```
Thus hash is not the best (weak avalanche effect). 

# Išvados:
## Privalumai:
- Visi hash'ai skirtingi, t.y. 0 kolizijų.
## Trūkumai:
- Nemažas average panašumas hex'ų lygyje, ir ypač didelis bit'ų lygyje
