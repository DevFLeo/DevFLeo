
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>Portfólio do Leonardo</title>
  <style>
    body {
      background-color: #121212;
      color: #eee;
      transition: all 0.3s ease;
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    }
    body.light {
      background-color: #f4f4f4;
      color: #222;
    }
    button {
      position: fixed;
      top: 1rem;
      right: 1rem;
      padding: 0.5rem 1rem;
      cursor: pointer;
    }
  </style>
</head>
<body>
  <button id="toggle-theme">Modo Claro</button>

  <h1>Olá, eu sou o Leonardo!</h1>
  <p>Este é meu portfólio com domínio infinito de temas.</p>

  <script>
    const button = document.getElementById('toggle-theme');
    const body = document.body;

    // Carrega tema salvo
    if(localStorage.getItem('theme') === 'light') {
      body.classList.add('light');
      button.textContent = 'Modo Escuro';
    }

    button.onclick = () => {
      body.classList.toggle('light');
      if(body.classList.contains('light')) {
        button.textContent = 'Modo Escuro';
        localStorage.setItem('theme', 'light');
      } else {
        button.textContent = 'Modo Claro';
        localStorage.setItem('theme', 'dark');
      }
    };
  </script>
</body>
</html>
