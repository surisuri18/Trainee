/**
 * Mini aplicación web con Node.js y Express
 * Funcionalidad:
 *  - Agregar libros a un archivo de texto (libros.txt)
 *  - Listar todos los libros
 *  - Evita libros duplicados
 */

const express = require("express");
const fs = require("fs");
const path = require("path");
const bodyParser = require("body-parser");

const app = express();
const PORT = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, "views")));

// Función para leer libros desde archivo
function obtenerLibros() {
  const filePath = path.join(__dirname, "libros.txt");
  if (!fs.existsSync(filePath)) return [];
  return fs.readFileSync(filePath, "utf-8")
    .split("\n")
    .map(l => l.trim())
    .filter(l => l !== "");
}

// Ruta para listar libros
app.get("/libros", (req, res) => {
  const libros = obtenerLibros();
  if (libros.length === 0) return res.send("<h2>No hay libros registrados</h2><a href='/'>Volver</a>");

  res.send(`<div class="container text-center mt-5">
    <h2>Lista de Libros</h2>
    <ul class="list-group mt-3">${libros.map(l => `<li class="list-group-item">${l}</li>`).join("")}</ul>
    <a href="/" class="btn btn-primary mt-3">Volver</a>
  </div>`);
});

// Ruta para agregar libros (evitando duplicados)
app.post("/agregar", (req, res) => {
  const { titulo } = req.body;
  if (!titulo || titulo.trim() === "") return res.send("El título no puede estar vacío. <a href='/'>Volver</a>");

  const libros = obtenerLibros();
  if (libros.includes(titulo.trim())) {
    return res.send(`El libro "${titulo}" ya existe. <a href='/'>Volver</a>`);
  }

  fs.appendFileSync(path.join(__dirname, "libros.txt"), titulo.trim() + "\n", "utf-8");
  res.send(`Libro agregado correctamente: <b>${titulo}</b><br><a href="/">Volver</a>`);
});

app.listen(PORT, () => console.log(`Servidor corriendo en http://localhost:${PORT}`));
