<?php
$Email=$_GET['usr'];
$pass=$_GET['pWord'];
$user = substr($Email, 0, strpos($Email, "@"));

$db= mysqli_connect("localhost","root","MyBass58","Portfolio") or die("Error ".mysqli_error());
$result = mysqli_query($db,"Select * From User WHERE User = '".$Email."' AND Password= '".$pass."'");
echo "Select * From User WHERE Email = '".$Email."' AND Password= '".$pass."'";
$data=mysqli_fetch_assoc($result);
$rows = mysqli_num_rows($result);
echo $rows;

if($rows==1)
{
session_start();
$_SESSION['User']=$Email;

session_write_close ();
header("location:Manage.php");
}
else
{
header("location:login.html");
}
mysqli_close($db);

?>
