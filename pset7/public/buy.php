<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST") //returns symbol and shares
    {
        //TODO
        // Check if # of shares is integer and # > 0
        if(!preg_match("/^\d+$/", $_POST["shares"]))
        {
           apologize("Please enter a valid amount of shares.");
        }
        
        // Get the price, name, symbol of the stock
        $stock = lookup($_POST["symbol"]);
        
        // 
        if ($stock === false)
        {
            apologize("Symbol not found.");
        }
        
        // Check cash    
        $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        $cash = $rows[0]["cash"];
        
        if($cash < $_POST["shares"] * $stock["price"])
        {
            apologize("You do not have sufficient funds.");
        }
        else // Update portfolio
        {
            // Update portfolio
            query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?, ?) 
            ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["shares"]);
            // Update cash
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["shares"]*$stock["price"], $_SESSION["id"]);
            // Log into history
            query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES(?, 'BUY', ?, ?, ?)"
                                                , $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
            /*
            if(query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]) === false)
            {
                query("UPDATE portfolios SET shares = shares + ? WHERE id = ? and symbol = ?", $_POST["shares"], $_SESSION["id"], $_POST["symbol"]);
                query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["shares"]*$stock["price"], $_SESSION["id"]);
            }
            else
            {
                query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["shares"]*$stock["price"], $_SESSION["id"]);
            }
            */
        }
   
        
        // render portfolio
        render("buy.php", ["shares" => $_POST["shares"] ,"stock" => $stock, "title" => "Buy"] );
    }    
    else
    {   
        // render portfolio
        render("buy_form.php", ["title" => "Buy"] );
    }
?>
