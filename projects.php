<?php



//list all variables
if($_GET['action']=='all')
{

$data=array(); //create array
$result=mysqli_query($db,"SELECT * FROM Projects ORDER BY ID DESC");

 while($row = mysqli_fetch_assoc($result))
  {
    $data[]=$row;
    ++$track;
  }
echo json_encode($data);
}
else if($_GET['action']=='project')
{

  $result=mysqli_query($db,"SELECT * FROM Projects WHERE ID ='".$_GET['ID']."'");
  $data= mysqli_fetch_assoc($result);


  echo json_encode($data);
}
elseif($_GET['action']=='run')
{

}

elseif($_GET['action']=='remove')
{

}
elseif($_GET['action']=='upvote')
{
  $inc=0;
  $result=mysqli_query($db,"SELECT * FROM Projects WHERE ID ='".$_GET['ID']."'");
  $up= mysqli_fetch_assoc($result);
  $inc=$up['upvotes'];
  $inc+=1;
  $result=mysqli_query($db,"UPDATE `Projects` SET upvotes ='".$inc."' WHERE ID='".$_GET['ID']."'");
  echo json_encode($up);

}
else{
  echo"did not enter if statement.";
}


?>
