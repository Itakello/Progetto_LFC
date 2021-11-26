# Brzozowski DFA minimization

## Come fornire l'input

L'input può essere fornito come :
1. Grammatica libera regolare (da `cin` o da `input.txt`)
   1. Verrà poi trasformato in DFA tramite `thompson_construction()`
2. DFA
3. NFA

### Tramite grammatica libera regolare

Inserire una grammatica a scelta, tale per cui :
* il non-terminale del primo driver sia lo *stato iniziale*
* i non-terminali siano una lettera maiuscola ($A...Z$)
* i terminali siano una lettera minuscola ($a...z$)
* il carattere ɛ sia un $\#$
* il carattere | sia sempre un $|$

Essendo una grammatica regolare dovrà avere produzioni tali che:
1. i driver delle varie produzioni siano composti solamente da un non-terminale
2. i body siano composti
   1. da un solo terminale ($A \to a$)
   2. da un terminale e un non-terminale ($A \to aB$)
   3. da una parola vuota ($A \to \epsilon$)

I caratteri possono essere intervallati :
* da uno spazio ` `
* da una virgola `,`
* da un trattino `-`

La grammatica può essere inserita:
* in un file `input.txt` da inserire nella cartella principale del progetto
* da linea di comando, inserendo un'ulteriore a capo `\n` dopo l'ultima produzione

Nel caso in cui NON esista il file, verrà letta da linea di comando.

_**NOTE**_ : Utilizzare il file `input-example.txt` per un'esempio

### Possibili errori

1. Non inserire il segno di produzione "->"
2. Inserire 2 simboli senza intervallo (legge solo il primo)
3. Inserire un driver terminale
4. Inserimento di spazi o altri caratteri dopo l'inserimento dell'ultimo elemento del body di una produzione

### Tramite DFA

### Tramite NFA

## Come fornire l'output



## Strutture dati e automi utilizzati


## Tipo di test fatti


