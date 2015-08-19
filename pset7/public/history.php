<?php

    // configuration
    require("../includes/config.php");
    
    $rows = query("SELECT transaction, tdt, symbol, shares, price FROM history WHERE id = ?", $_SESSION["id"]);
    

    // render portfolio
    render("history.php", ["rows" => $rows, "title" => "History"] );

?>
