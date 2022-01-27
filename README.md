===== Aluna 1 =====
Stephanie Briere Americo
GRR: 20165313
Login dinf: sba16

===== Aluna 2 =====
Talita Halboth Cunha Fernandes
GRR: 20165399
Login dinf: thcf16

Constantes:
MAX_VALOR = o valor máximo que um elemento pode ter

** Representação dos conjuntos **
A representação escolhida para os conjuntos foi bit array. Mais especificamente: cada conjunto é um vetor de long int, e cada bit do vetor representa um número.
Antes de começar o desenvolvimento do projeto, consideramos as vantagens e desvantagens de diversas formas de representação de conjuntos, tendo como prioridade o desempenho do programa (tempo de execução).
- Vantagens
A principal vantagem do bit array é o tempo minimizado para comparação de conjuntos. Como usamos um vetor de long int, é possivel comparar 64 bits de uma vez só - ou seja, 64 possíveis elementos do conjunto. Essa característica se mostra extremamente vantajosa ao (em muitos casos) detectar a diferença entre dois conjuntos mais rapidamente que uma comparação elemento a elemento. Conforme os conjuntos se tornam grandes e semelhantes, a comparação em massa de 64 possíveis elementos começa a fazer uma grande diferença no tempo de execução. O número máximo de comparações (pior caso) sempre será MAX_VALOR/64, ou seja, quando os conjuntos são iguais.
- Desvantagens
Em contrapartida, essa representação exigirá mais comparações que uma representação em vetores normal (1 elementos por bloco) em alguns casos. Por exemplo: quando os conjuntos possuem menos elementos que MAX_VALOR/64 e são iguais, uma representação que permita comparar só os elementos que o conjunto possui é mais eficaz. Apesar de comparar 64 possiveis elementos de uma só vez, recuperar os elementos que DE FATO estão no conjunto possui o custo de percorrer MAX_VALOR bits e verificar se estão ligados. 

Como a comparação de conjuntos é utilizada em quase todas as outras operações, é essencial que ela seja rápida. Sendo assim, consideramos que a vantagem dessa representação é maior que a desvantagem, dado o problema de representação de conjuntos - a quantidade de casos ótimos tende a superar a quantidade de piores casos.

** Representação da coleção **
A coleção de conjuntos é representada em um vetor indexado por [tamanho_dos_conjuntos - 1]. Ou seja: conjuntos de tamanho 1 encontram-se na coleção[0]. Separar os conjuntos com o mesmo tamanho nos pareceu vantajoso, pois reduz o tempo de busca por conjuntos específicos dentro da coleção e torna mais barata a remoção de conjuntos.

** Dificuldades **
As maiores dificuldades estão no fato de que nos recusamos a utilizar funções/estruturas prontas. Os motivos são dois:
(i) preferimos aprender a fazer todo e cada método/estrutura antes de utilizar um pronto (bit array e seus métodos de inserção/remoção, binary search...);
(ii) ao fazer nossos próprios métodos/estruturas, podemos evitar que as implementações contenham funcionalidades desnecessárias (para o nosso contexto) que possam reduzir o desempenho do programa.
Em particular, as representações escolhidas exigem muita manipulação de ponteiros. 
/* Muito overflow, segmentation flow, depuração de código e valgrind para liberar toda a memória no fim do código */

** Considerações **
Muitas decisões de projeto foram tomadas visando um melhor desempenho - até mesmo algumas pequenas, como o fato de que liberamos a memória apenas no fim do programa, evitando alocar mais de uma vez a mesma memória. O exercício de considerar cada decisão com o objetivo de aumentar o desempenho foi de grande aprendizado para o grupo.
