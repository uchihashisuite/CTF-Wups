<?php

if (isset($_SESSION["name"])) {
  header("Location: home.php");
  die();
}

if (isset($_POST["name"])) {
  $_SESSION["name"] = $_POST["name"];
  header("Location: home.php");
  die();
}else{
  require_once("./vendor/autoload.php");

  $loader = new \Twig\Loader\FilesystemLoader('templates');

  $twig = new \Twig\Environment($loader, []);

  $result = $twig->render("index.html", []);
  echo $result;
}

?>
