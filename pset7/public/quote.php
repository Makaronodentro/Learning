<?php
    
    // configuration
    require("../includes/config.php");
    
    // TODO: Check if logged in
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    
        $stock = lookup($_POST["symbol"]);
        
        if ($stock === false)
        {
            apologize("Symbol not found.");
        }
        else
        {
            $stock["price"] = number_format($stock["price"], 4);
            render("quote.php", ["title" => "Quote", "price" => $stock["price"], "symbol" => $stock["symbol"], "name" => $stock["name"], "currency" => $stock["currency"]]);
        }     
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
?>
