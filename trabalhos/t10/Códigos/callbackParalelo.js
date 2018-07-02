const fs = require("fs");

var contador = 0;
//Variáveis que guardam o resultado de cada leitura, já que não se tem controle de qual leitura terminará primeiro
var leitura1, leitura2;
//O contador é incrementado a cada início de leitura e decrementao no fim, quando ele chegar a 0 significa que encerrou a leitura e pode imprimir
contador++;
console.time("Tempo Execução Paralela Total");
fs.readFile('./arquivo1.txt', function(err, dados) {
	contador--;
	
	if (err) {
		return console.log(err);
	}
	else {
		leitura1 = dados;

		if (contador == 0) {
			console.log('\n' + leitura1 + '\n\n' + leitura2);
		}
	}
});

contador++;
fs.readFile('./arquivo2.txt', function(err, dados) {
	contador--;

	if (err) {
		return console.log(err);
	}
	else {
		leitura2 = dados;

		if (contador == 0) {
			console.log('\n' + leitura1 + '\n\n' + leitura2);
		}
	}
});
console.timeEnd("Tempo Execução Paralela Total");