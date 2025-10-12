<?php

if (isset($_GET["vuln"]) && is_string($_GET["vuln"]))
{
  $vuln_number = $_GET["vuln"];
  if($vuln_number === "1")
    $output = hash('sha3-512' , trim(file_get_contents("/flag1")));
  else if($vuln_number === "2")
    $output = hash('sha3-512' , trim(shell_exec("/readflag")));

  echo $output;
}

?>