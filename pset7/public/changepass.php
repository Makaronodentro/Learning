<?php
    
    // configuration
    require("../includes/config.php");
    
    // TODO: Check if logged in
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if empty fields apologize
        if(empty($_POST["current_pass"]))
        {
            apologize("Please enter your old password.");
        }
        elseif(empty($_POST["new_pass1"]) || empty($_POST["new_pass2"]))
        {
            apologize("Please enter your new password in both fields.");
        }
    
        // query database for user password
        $rows = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);

        // Check if the correct current password was entered
        if(crypt($_POST["current_pass"], $rows[0]["hash"]) != $rows[0]["hash"])
        {
            apologize("Please re-enter your old password.");
        }
        // Check if the new two passwords match
        if ($_POST["new_pass1"] !== $_POST["new_pass2"])
        {
            apologize("Your new passwords don't match.");
        }
        // Procceed with password change
        else
        {
            // Change the password hash in the database
            query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_pass1"]), $_SESSION["id"]);
            render("changepass.php", ["title" => "Password Changed"]);
        }     
    }
    else
    {
        // else render form
        render("changepass_form.php", ["title" => "Change Password"]);
    }
    
?>
