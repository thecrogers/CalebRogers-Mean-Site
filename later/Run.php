<?php
 $db= mysqli_connect("localhost","root","MyBass58","Portfolio") or die("Error ".mysqli_error());
 $data=array(); //create array
 $result=mysqli_query($db,"SELECT * FROM Projects GROUP BY ID");
while($row = mysqli_fetch_assoc($result))
   {
     $data[]=$row;
   }
//var_dump($data);
$code=$_GET['ID'];
$input=$_GET['args'];
$num=1;
$code-=$num;
$Result=array();
//echo $code;
if(is_numeric($input)&& isset($data[$code]['SRC']))
{
$output = shell_exec("./".$data[$code]['SRC']." ".$input." 2>&1");
$Result['result']=$output;
//var_dump($result);
//echo $Result;
echo json_encode($Result);
}
else
{
echo "that inputis not excepted.";
}
?>
