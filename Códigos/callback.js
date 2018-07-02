const fs = require("fs");

console.time("Tempo Execução Sequencial do arquivo");
//Leitura do arquivo1.txt, se não ocorrer nenhum erro ele passa a ler o arquivo2
fs.readFile('./arquivo1.txt', function(err, arquivo1) { 
	if (err) {
		return console.log(err);
	}
	else {
		fs.readFile('./arquivo2.txt', function(err, arquivo2) { 
			if (err) {
				return console.log(err);
			}
			//Imprime os textos dos dois arquivos
			console.log('\n' + arquivo1 + '\n\n' + arquivo2);
		});
	}
	console.timeEnd("Tempo Execução Sequencial do arquivo");
});