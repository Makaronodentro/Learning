<?php

    // configuration
    require("../includes/config.php");
    
    $rows = query("SELECT symbol, shares FROM portfolios WHERE id = ?", $_SESSION["id"]);
    $c = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "currency" => $stock["currency"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => $stock["price"]*$row["shares"]
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["cash" => $c, "positions" => $positions, "title" => "Portfolio"] );

?>
