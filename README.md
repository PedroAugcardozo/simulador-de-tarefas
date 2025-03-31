## Gerenciador de Tarefas com Fila de Prioridades

Este projeto simula um sistema de gerenciamento de tarefas para uma fábrica de brinquedos, utilizando uma fila de prioridades para organizar e processar tarefas de acordo com seu nível de urgência. O programa lê tarefas de um arquivo de texto, distribui entre os operadores disponíveis e exibe estatísticas ao final da simulação.

📌 Funcionalidades

Fila de prioridades para organizar tarefas (Urgente, Normal e Opcional).

Simulação do processamento das tarefas por operadores.

Exibição do estado do sistema em cada unidade de tempo.

Geração de estatísticas ao final da simulação:

Número total de tarefas concluídas por tipo.

Tempo médio de espera para cada tipo de tarefa.

Número de tarefas não concluídas.

🛠️ Tecnologias Utilizadas

C++ para implementação da lógica.

conio2 para exibição da interface no console (biblioteca não padrão do C++).

📂 Estrutura do Arquivo de Entrada (tarefas.txt)

O arquivo de entrada contém as tarefas no seguinte formato:

Tipo,TempoConclusao,DescricaoTarefa
Urgente,30,Reparar maquina de montagem
Normal,15,Montar carrinho de madeira
Opcional,60,Treinar equipe em nova maquina

📌 Campos:

Tipo: Urgente, Normal ou Opcional.

TempoConclusao: Tempo estimado de conclusão (minutos).

DescricaoTarefa: Descrição detalhada da tarefa.

🚀 Como Executar o Projeto

1️⃣ Instalar a Biblioteca conio2

Este projeto utiliza a biblioteca conio2, que não é padrão no C++. Você precisa instalá-la antes de compilar o código. Para instalar:

Baixe o arquivo conio2.h e conio2.c.

Adicione-os ao diretório do seu projeto.

Inclua #include "conio2.h" no seu código.
