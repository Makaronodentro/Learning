<div>

    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>

</div>
<div>
<table class="table table-bordered">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
    </thead>
    
    <tbody>
    <?php foreach ($positions as $position): ?>
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["currency"]." ".number_format($position["price"], 2) ?></td>
            <td><?= $position["currency"]." ".number_format($position["total"], 2) ?></td>
        </tr>

    <?php endforeach ?>
        <tr>
            <td>CASH</td>
            <td> </td>
            <td> </td>
            <td> </td>
            <td>USD <?php foreach ($cash as $c) {echo number_format($c["cash"], 2);} ?> </td>
        </tr>
    </tbody>
    
</table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
<div>
    <a href="changepass.php">Change Password</a>
</div>
