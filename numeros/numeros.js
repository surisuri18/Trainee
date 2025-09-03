function ordenarUnicos(lista) {
  // new Set elimina duplicados, Array.from lo convierte en array
  return Array.from(new Set(lista)).sort((a, b) => a - b); //estudiarlo
}

//  uso
const entrada = [4, 2, 7, 2, 4, 9, 1];
const salida = ordenarUnicos(entrada);
console.log(salida); // [1, 2, 4, 7, 9]

