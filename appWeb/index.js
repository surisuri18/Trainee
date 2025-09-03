

const express = require("express");
const fs = require("fs");
const path = require("path");
const bodyParser = require("body-parser");

const app = express();
const PORT = 3000;

// Middleware para procesar datos de formularios (req.body)
app.use(bodyParser.urlencoded({ extended: true }));

// Carpeta de archivos estáticos (para servir el HTML)
app.use(express.static(path.join(__dirname, "views")));

// Ruta para obtener la lista de libros
app.get("/libros", (req, res) => {
  const filePath = path.join(__dirname, "libros.txt");

  // Si no existe el archivo, devolvemos lista vacía
  if (!fs.existsSync(filePath)) {
    return res.send("No hay libros registrados.");
  }

  const data = fs.readFileSync(filePath, "utf-8");
  const libros = data.split("\n").filter((line) => line.trim() !== "");

  res.send(`<h2>Lista de Libros</h2><ul>${
    libros.map((libro) => `<li>${libro}</li>`).join("")
  }</ul><a href="/">Volver</a>`);
});

// Ruta para agregar un libro
app.post("/agregar", (req, res) => {
  const { titulo } = req.body;

  if (!titulo || titulo.trim() === "") {
    return res.send("El título no puede estar vacío. <a href='/'>Volver</a>");
  }

  const filePath = path.join(__dirname, "libros.txt");

  // Guardamos el libro en el archivo (modo append)
  fs.appendFileSync(filePath, titulo + "\n", "utf-8");

  res.send(`Libro agregado correctamente: <b>${titulo}</b><br><a href="/">Volver</a>`);
});

// Iniciar el servidor
app.listen(PORT, () => {
  console.log(`Servidor corriendo en http://localhost:${PORT}`);
});
