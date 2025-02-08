# Trabalho Compiladores

Esse trabalho foi feito para a disciplina de Compiladores em 2024/2 na UFRGS.
O objetivo é transformar um código em uma linguagem (chamada aqui de 2024++2) em código de máquina AT&T testado em Ubuntu.

## Definição da linguagem

Um programa na linguagem 2024++2 é composto por uma lista global de declarações que podem ser declarações de variáveis, de vetores ou de funções, em qualquer ordem, mesmo intercaladas. O corpo das funções é um bloco com uma lista de comandos, que podem ser de atribuição, controle de fluxo ou os comandos **read**, **print** e **return**.
Os tipos **int** e **char** são intercambiáveis, podem ser usados no lugar do outro a qualquer momento.

### Definições Léxicas
Identificadores (nomes de variáveis e funções) são uma sequência de caracteres que podem ser digitos de **0** a **9** e caracteres de **A** a **z**.
Literais inteiro são definidos como um número com **#** na frente, como **#0**.
Literais caractere são definidos como um caractere entre aspas simples, como **'a'**.
Literais string são definidos como um conjunto de caracteres em aspas duplas, como **"Olá Pessoal"**.

A linguagem também permite comentários de única linha, com **//** e comentários de múltiplas linhas com **/**** e ****/**.

### Definições sintáticas
- Variáveis só podem ser declaradas fora de funções (ou seja, globais) e precisam ter tipo *int* ou *char* e um valor inicial, que pode ser int ou char.
- Declaração de variáveis é assim:
> int var = #0;
char 1 = 'a';

- Declaração de vetor pode ou não ter valores iniciais, separados por espaço e deve ter o tamanho do vetor.
> int vetor[#5];
char vetChar[#3] = 'a' #0 #1;

- Parâmetros de função precisam ter nomes de variável únicos.
- Ao final de cada comando é necessário um ponto e vírgula **;**

## Comandos
- **while (expr) {[comandos\]}**
*expr* precisa resultar em um valor booleano.
*comandos* pode ser um comando sem chaves **{ }** ou uma lista de comandos com chaves **{ }**.
Vai repetir os comandos até que expr seja falso.

- **if (expr) then {cmd} else {cmd2}**
*expr* precisa resultar em um valor booleano.
Pode ou não ter a parte do *else {cmd2}*.
Essa expressão vai executar *{cmd}* se expr for verdadeiro e {cmd2} se for falso.

- **read id;**
*id* é um identificador.
Lê um caractere do teclado e armazena em id.

- **print <arg1\> [arg2\] [arg3\]... ;**
Precisa ter pelo menos 1 argumento.
Imprime na tela os argumentos, que podem ser char, int ou string.

- **return expr**
Encerra a função executada atual e retorna o valor da expressão.

- **Atribuição**
É feita da forma:
> id = expr;

expr precisa ter um tipo compatível com *id*.
A variável *id* vai receber o valor de *expr*.

- **Expressões**
Podem ser, um identificador, uma função, expressões aritméticas
(**+ - * /**), expressões booleanas (**> < = & | ~**).
Expressões aritméticas **não** se juntam com booleanas e vice-versa.


## Passos de Execução

Não tenho como objetivo fazer esse trabalho ser acessível para executar em outros computadores. Mas se você quiser tentar, aqui eu explico como fazer isso:

### Requisitos
Precisa ter Make, Flex, Bison e GCC para rodar. Eu usei Ubuntu em um computador Windows por WSL e não precisei instalar nada.

### Make
Abra o prompt de comando na pasta com os arquivos e escreva
> make

Isso deve compilar todos os códigos necessários. Se der um erro, pode ser que você não tenha algum programa necessário.

### Executar o programa
- Escreva o código na linguagem 2024++2 em um arquivo .txt na mesma pasta com os arquivos.
- Após isso, execute o seguinte comando no prompt de comando:
> ./etapa6 \<entrada.txt\> <saida.s\>

Em que a entrada é o arquivo **com a extensão** criado anteriormente e a saída é um arquivo que vai ser criado, com a extensão **.s**.
Isso vai gerar o código de máquina do código da entrada no arquivo de saída.
* Finalmente, compile o código com g++ para gerar o código executável, com o seguinte comando:
> g++ <saida.s\> [-o <nome do executavel\>]

Adicionalmente pode escolher um nome do executável no comando, se não escolher, o nome padrão é **a.out**.

* Agora, ao executar o arquivo criado (o nome escolhido ou a.out) se tudo deu certo, é para o código de entrada ser rodado no terminal.
> ./a.out
