<?php

function http_client($url){
  $curl = curl_init();
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 3);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($curl, CURLOPT_FOLLOWLOCATION, true);
  curl_setopt($curl, CURLOPT_FAILONERROR, true);
  curl_setopt($curl, CURLOPT_HEADER, false);

  $data = curl_exec($curl);
  curl_close($curl);

  return $data;
}


if(isset($_GET["url"]) && $_GET["url"] !== ""){
  $data = http_client($_GET["url"]);

  echo $data;
}else{
  require_once("./vendor/autoload.php");
  $loader = new \Twig\Loader\FilesystemLoader('templates');

  $twig = new \Twig\Environment($loader, []);

  $result = $twig->render("viewer.html", []);
  echo $result;
}


?>
