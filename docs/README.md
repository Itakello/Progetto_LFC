# Brzozowski DFA minimization

## Come fornire l'input

L'input può essere fornito come :
1. Grammatica (da `cin` o da `input.txt`)
2. DFA
3. NFA

### Tramite grammatica

Inserire una grammatica a scelta, tale per cui :
* il primo non-terminale sia lo *stato iniziale*
* i non-terminali siano una lettera maiuscola (A...Z)
* i terminali siano una lettera minuscola (a...z)
* il carattere ɛ sia un #
* il carattere | sia sempre un |

I caratteri possono essere intervallati :
* da uno spazio ` `
* da una virgola `,`
* da un trattino `-`

La grammatica può essere inserita:
* in un file `input.txt` da inserire nella cartella principale del progetto
* da linea di comando, inserendo un doppio a capo alla fine della grammatica

Nel caso in cui NON esista il file, verrà letta da linea di comando.

_**NOTE**_ : Utilizzare il file `input-example.txt` per un'esempio

### Possibili errori

1. Non inserire il segno di produzione "->"
2. Inserire 2 simboli senza intervallo (legge solo il primo)
3. Driver senza simbolo non-terminale
4. Inserimento di troppi simboli driver o body (>30)

### Tramite DFA

### Tramite NFA

## Come fornire l'output



## Strutture dati e automi utilizzati

1. Vector, utilizzato per :
   1. Vocaboli nelle produzioni
   2. Produzioni nella grammatica

## Tipo di test fatti


