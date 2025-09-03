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

app.use(express.json()); // para JSON
app.use(express.json());
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

// Ruta para obtener lista de libros en JSON
app.get("/libros", (req, res) => {
  const libros = obtenerLibros();
  res.json({ libros });
});

// Ruta para agregar libros (evitando duplicados)
app.post("/agregar", (req, res) => {
  const { titulo } = req.body;
  if (!titulo || titulo.trim() === "") {
    return res.status(400).json({ error: "El título no puede estar vacío." });
  }

  const libros = obtenerLibros();
  if (libros.includes(titulo.trim())) {
    return res.status(400).json({ error: `El libro "${titulo}" ya existe.` });
  }

  fs.appendFileSync(path.join(__dirname, "libros.txt"), titulo.trim() + "\n", "utf-8");
  res.json({ mensaje: `Libro agregado correctamente: ${titulo}` });
});

app.listen(PORT, () => console.log(`Servidor corriendo en http://localhost:${PORT}`));
