## Dicas para realizar o laboratório

Este laboratório foi pensado para que você descubra os resultados por meio
da experimentação. Antes de procurar a resposta, execute os programas e
observe as saídas.

### 1. Comece pela aposta

Antes de executar os programas, responda às questões Q1, Q2 e Q3 do roteiro.

Não tente descobrir a resposta executando vários comandos aleatoriamente.
A ideia é registrar primeiro sua hipótese e depois confrontá-la com os
resultados experimentais.

---

### 2. Estação 1 — `dissect`

O programa `dissect` recebe um número como argumento.

Exemplo:

```bash
./dissect 0.1
```

Experimente também:

```bash
./dissect 0.2
./dissect 0.3
./dissect 1.0
```

No Windows:

```powershell
.\dissect.exe 0.1
```

Observe principalmente:

* `valor digitado`
* `valor guardado`
* `hexadecimal`
* `bits`
* `sinal`
* `expoente bruto`
* `expoente real`
* `CLASSIFICACAO`

**Dica:** compare o `valor digitado` com o `valor guardado`.
Eles são exatamente iguais?

Depois observe os 32 bits. Lembre-se de que um `float` IEEE-754 possui:

```text
1 bit       8 bits             23 bits
┌─────┬───────────────┬───────────────────────┐
│sinal│   expoente    │        fração         │
└─────┴───────────────┴───────────────────────┘
   31       30 ... 23          22 ... 0
```

Não se preocupe em decorar tudo de uma vez. Use a saída do programa
como evidência para responder às perguntas.

---

### 3. Estação 2 — `patriot`

Execute:

```bash
./patriot
```

No Windows:

```powershell
.\patriot.exe
```

Observe a diferença entre:

```text
float
double
```

Pergunte a si mesmo:

> Se a mesma operação for realizada com diferentes precisões,
> o resultado precisa ser exatamente igual?

**Dica:** não olhe apenas para a quantidade de casas decimais.
Observe o valor numérico produzido e compare os resultados.

---

### 4. Estação 3 — `monstros`

Execute:

```bash
./monstros
```

No Windows:

```powershell
.\monstros.exe
```

O programa `monstros` **não recebe números como argumentos**.

Portanto, comandos como:

```bash
./monstros 1
./monstros 2
./monstros 10
```

não selecionam experimentos diferentes. Os argumentos adicionais serão
ignorados pelo programa atual.

Execute simplesmente:

```bash
./monstros
```

O programa realizará automaticamente uma sequência de experimentos.

Observe separadamente:

1. `+0.0` e `-0.0`
2. infinito
3. `NaN`
4. `FLT_EPSILON`
5. absorção
6. não associatividade

**Dica:** não tente entender todos os experimentos de uma vez.
Para cada saída, pergunte:

> "O que eu esperava que acontecesse?"

e depois:

> "O que realmente aconteceu?"

---

### 5. Não confunda `FLT_EPSILON` com o menor `float`

Um cuidado importante:

```text
FLT_EPSILON
```

não significa simplesmente "o menor número que um `float` consegue
representar".

Observe como o programa utiliza esse valor e compare os experimentos
realizados próximos de `1.0f`.

---

### 6. Para a questão da absorção

Preste atenção especialmente aos experimentos envolvendo:

```text
1e7 + 1.0
1e8 + 1.0
```

Compare:

```text
valor antes
valor depois
mudou?
```

**Pergunta-guia:**

> O que acontece quando tentamos somar um número muito pequeno a um
> número muito grande usando uma representação de precisão finita?

Não basta marcar a alternativa. Tente explicar o fenômeno usando
`float`, arredondamento e precisão.

---

### 7. Para a não associatividade

Observe atentamente as expressões:

```text
(a + b) + c
```

e

```text
a + (b + c)
```

Matematicamente, a soma é associativa.

Mas o laboratório não está trabalhando com números reais ideais:

```text
ℝ
```

e sim com uma representação de precisão finita:

```text
float
```

**Dica:** faça as duas expressões passo a passo e compare o que
acontece em cada operação intermediária.

---

### 8. Use a saída como evidência

Nas respostas do relatório, evite escrever apenas:

> "Porque o float tem erro."

Isso é insuficiente.

Procure construir suas respostas utilizando evidências observadas
nos programas.

Uma boa resposta deve seguir, sempre que possível, esta estrutura:

```text
O que eu esperava
        ↓
O que o programa mostrou
        ↓
O que mudou
        ↓
Por que isso aconteceu
```

---

### 9. Não altere a compilação da Estação 3

Não utilize:

```bash
-ffast-math
```

na compilação dos programas deste laboratório.

Esse tipo de otimização pode permitir que o compilador faça suposições
sobre a aritmética de ponto flutuante que alterem justamente os
comportamentos que estamos investigando.

Compile normalmente:

```bash
gcc -Wall -Wextra -std=c11 -O2 ...
```

---

### 10. Se algo parecer estranho, não descarte o resultado

Neste laboratório, alguns resultados foram escolhidos justamente porque
contradizem a nossa intuição matemática.

Se o computador apresentar algo inesperado:

1. não altere imediatamente o código;
2. registre a saída;
3. tente explicar o comportamento;
4. compare com os conceitos estudados;
5. somente depois discuta possíveis diferenças de ambiente.

O objetivo não é fazer o computador "dar a resposta esperada".

O objetivo é entender **por que ele produziu aquela resposta**.

## Checklist

Antes de pedir ajuda, verifique:

- [ ] Compilei os três programas sem erros.
- [ ] Executei `dissect` com pelo menos três valores diferentes.
- [ ] Comparei `valor digitado` e `valor guardado`.
- [ ] Observei os 32 bits do `float`.
- [ ] Executei `patriot`.
- [ ] Comparei `float` e `double`.
- [ ] Executei `monstros` sem argumentos.
- [ ] Observei os seis experimentos.
- [ ] Registrei minhas observações.
- [ ] Fiz minhas apostas antes dos experimentos.
- [ ] Tentei explicar os resultados, e não apenas copiá-los.
