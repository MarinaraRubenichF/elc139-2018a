# T5: Aplicação do Método de Monte Carlo em OpenMP

## Pastas

1. A [Pasta 1](1.FireSim_Seq) contém o programa original, sequencial.

2. A [Pasta 2](2.FireSim_OpenMP1) contém a 1ª solução paralelizada do programa.

3. A [Pasta 3](3.FireSim_OpenMP2) contém a 2ª solução paralelizada do programa.

## Detalhes sobre o ambiente

**Sistema Operacional:**  
Windows 10 Home Single Language

**Ferramentas:**  
Dev-C++ 5.11  
Cygwin 2.10.0  
g++ (GCC) 6.4.0

**Arquitetura:**  
Intel® Core™ i5-6200U  
2,2 GHz até 2,7 GHz  
2 núcleos, 2 threads por núcleo  
4GB RAM, 1TB HD  
3MB Cache L3
Mais detalhes [aqui](https://ark.intel.com/products/85212/Intel-Core-i5-5200U-Processor-3M-Cache-up-to-2_70-GHz).

## Resultados

### Solução 1

* Realizar a divisão dos cálculos das médias dos percentuais de árvores queimadas entre as threads existentes deixando a separação das iterações para cada thread a cargo do compilador.

  * Para problema Grande: `./firesim 60 2000 75`  

    | Nº Threads | Tempo | SpeedUp | Eficiência |
    | :--------: | :---: | :-----: | :--------: |
    | 1          | 2,94m | -       | -          |
    | 2          | 2,51m | 1,16    | 0,58       |
    | 4          | 1,74m | 1,69    | 0,42       |

  * Para problema Médio: `./firesim 50 1500 65`  

    | Nº Threads | Tempo | SpeedUp | Eficiência |
    | :--------: | :---: | :-----: | :--------: |
    | 1          | 1,20m | -       | -          |
    | 2          | 1,01m | 1,18    | 0,59       |
    | 4          | 39,03s| 1,84    | 0,46       |

  * Para problema Pequeno: `./firesim 30 1000 50`  

    | Nº Threads | Tempo | SpeedUp | Eficiência |
    | :--------: | :---: | :-----: | :--------: |
    | 1          | 9,11s | -       | -          |
    | 2          | 7,82s | 1,16    | 0,58       |
    | 4          | 5,33s | 1,70    | 0,42       |
  
### Solução 2

* Realizar a divisão da execução de experimentos entre as threads existentes também deixando a separação das iterações para cada thread a cargo do compilador.

  * Para problema Grande: `./firesim 60 2000 75`  

    | Nº Threads | Tempo | SpeedUp | Eficiência |
    | :--------: | :---: | :-----: | :--------: |
    | 1          | 3,003m| -       | -          |
    | 2          | 1,88m | 1,59    | 0,79       |
    | 4          | 1,34m | 2,23    | 0,55       |

  * Para problema Médio: `./firesim 50 1500 65`  

    | Nº Threads | Tempo | SpeedUp | Eficiência |
    | :--------: | :---: | :-----: | :--------: |
    | 1          | 1,19m | -       | -          |
    | 2          | 43,77s| 1,63    | 0,81       |
    | 4          | 32,36s| 2,20    | 0,55       |

  * Para problema Pequeno: `./firesim 30 1000 50`  

    | Nº Threads | Tempo | SpeedUp | Eficiência |
    | :--------: | :---: | :-----: | :--------: |
    | 1          | 8,90s | -       | -          |
    | 2          | 5,66s | 1,57    | 0,78       |
    | 4          | 4,30s | 2,06    | 0,51       |
    
## Conclusão

* Ao meu ver valeu a pena paralelizar este programa, os resultados mostram o ganho de desempenho que temos ao fazer isso e são pouquíssimas linhas acrescentadas, deu trabalho para achar a solução, mas depois foi tranquilo de implementar.  
Para a Solução 1 quando são utilizadas 4 threads temos um bom gano de desempenho, porém quando se tem 2 threads não existe um grande ganho de desempenho, então vai do programador querer utilizar OpenMP ou não, eu utilizaria, qualquer pequeno ganho de desempenho (se a análise não for muito complexa), ao meu ver, é válido. Já solução 2 apresentou excelentes resultados seja utilizando 1 ou 2 threads.
 
### Obs.:

*Para compilar qualquer um dos programas de qualquer uma das pastas, no terminal faça:*  
`make`  
`./firesim <tamanho-do-problema> <nro. experimentos> <probab. maxima>`  

*Exemplo:* `./firesim 30 5000 101`
