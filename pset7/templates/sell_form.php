<form name="symbol" action="sell.php" method="POST">
    <fieldset>
        <legend>Current stocks held:</legend>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option value=""> </option>
                <?php foreach ($positions as $position)
                    print("<option value=".$position["symbol"].">".$position["symbol"]."</option>");
                ?>
            </select>
        </div>
         <div class="form-group">
            <input autofocus class="form-control" name="shares" placeholder="Number of Shares" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
