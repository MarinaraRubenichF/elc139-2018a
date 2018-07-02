const async = require("async");

//Função que exibe no terminal uma mensagem (string) que é passada por parâmetro após passarem 3s
function exibeMensagem(mensagem, callback) {
	setTimeout(function() {
		console.log(mensagem);
		callback();
	}, 3000);
}

//Código Single - Ele recebe a primeira mensagem e imprime, então aguarda estar liberado para receber a segunda
console.time("Execução Sequencial");
exibeMensagem("\nMensagem Async Sequencial: 'É assim que funciona com o async sequencial!'\n", function() {
	exibeMensagem("\nMensagem Async Sequencial: 'Eu trabalho sozinho, viu como demoro um pouco mais?'\n", function() {
		console.timeEnd("Execução Sequencial");
	});
});

//Código Paralelo - Neste caso ele pode receber e imprimir as duas mensagens ao mesmo tempo. Sem a necessidade de Callbacks aninhados
console.time("Execução paralela");
async.parallel([
	function(callback) {
		exibeMensagem("\nMensagem Async Paralela: 'É assim que funciona com o async paralelizado!'\n", function() {
			callback();
		});
	},
    
	function(callback) {
		exibeMensagem("\nMensagem Async Paralela: 'Aqui tudo funciona muito mais rápido! E de uma vez só!'\n", function() {
			callback();
		});
	}
],  function() { 
		console.timeEnd("Execução paralela"); 
});