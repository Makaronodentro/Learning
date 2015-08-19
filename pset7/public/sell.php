<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //TODO what happens if form submitted
        // Check if number of shares provided is valid
        if(!preg_match("/^\d+$/", $_POST["shares"]))
        {
           apologize("Please enter a valid amount of shares.");
        }
     
        // Get the number of shares owned
        $rows = query("SELECT shares FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        $shares = $rows[0]["shares"];
        
        if($shares < $_POST["shares"])
        {
            apologize("You don't have that many shares to sell.");
        }
        
        // Get the price of the stock
        $stock = lookup($_POST["symbol"]);
        
        // Update portfolio
        if($shares == $_POST["shares"])
        {
            query("DELETE FROM portfolios WHERE id = ? AND symbol = ?",$_SESSION["id"], $_POST["symbol"]);
        }
        else
        {
            query("UPDATE portfolios SET shares = shares - ? WHERE id = ? AND symbol = ?",$_POST["shares"], $_SESSION["id"], $_POST["symbol"]); 
        }
        
        // Add Cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?",$_POST["shares"]*$stock["price"], $_SESSION["id"]);
        
        // Log into history
        query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES(?, 'SELL', ?, ?, ?)"
                                            , $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
    
        // render portfolio
        render("sell.php", ["shares" => $_POST["shares"] ,"stock" => $stock, "title" => "Sale"] );
    }    
    else
    {
        $rows = query("SELECT symbol FROM portfolios WHERE id = ?", $_SESSION["id"]);
    
        $positions = [];
        foreach ($rows as $row)
        {
            $positions[] = [
                "symbol" => $row["symbol"],
                ];
        }   
        
    
        // render portfolio
        render("sell_form.php", ["positions" => $positions, "title" => "Sell"] );
    }
?>
