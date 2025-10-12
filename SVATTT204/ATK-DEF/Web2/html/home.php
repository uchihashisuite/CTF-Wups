<?php

if (!isset($_SESSION["name"])) {
  header("Location: index.php");
}

if(isset($_FILES["file"])){
  if(!isset($_SESSION["storage"])){
    $_SESSION["storage"] = bin2hex(random_bytes(32));
  }

  $file_path = __DIR__ . "/uploads/" . $_SESSION["storage"];
  if(!file_exists($file_path)){
    mkdir($file_path);
  }

  if(move_uploaded_file($_FILES["file"]["tmp_name"], $file_path . "/" . $_FILES["file"]["name"])){
    header("Location: home.php");
    die($_FILES["file"]["name"]);
  }else{
    die("error");
  }

}else{
  require_once("./vendor/autoload.php");

  $loader = new \Twig\Loader\FilesystemLoader('templates');
  
  $twig = new \Twig\Environment($loader, []);
  
  $result = $twig->render("home.html", ["name"=>$_SESSION["name"]]);
  echo $result;
}

?>