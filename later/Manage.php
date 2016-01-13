<?php
session_start();
if (isset($_SESSION['User'])) {
   $_SESSION['User'];
   $_SESSION['Name'];
 } else {
    header("location:login.html");
 }
echo'
<!DOCTYPE html>
<html lang ="en" ng-app="portfolio">
<head>
  <meta charset=utf-8">
  <title>Caleb W Rogers | Programmer & Web Developer | Dallas</title>
  <meta property="og:locale" content="en_US">
  <meta property="og:type" content="artical">
  <meta property="og:title" content="Caleb W Rogers | Programmer & Web Developer | Dallas">
  <meta property="og:description" content="">
  <meta name="HandheldFriendly" content="True">
  <meta name="MobileOptimized" content="320">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
    <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <script src="javascript/custom.js"></script>
    <![endif]-->
    <link rel="stylesheet" href="/stylesheets/bootstrap.min.css">
    <link rel="stylesheet" href="/stylesheets/bootstrap-theme.min.css">
    <link rel="stylesheet" href="/stylesheets/custom.css">
    <script src="javascripts/angular.min.js"></script>
    <script src="javascripts/angular-ui-router.js"></script>
    <script src="javascripts/dirPagination.js"></script>

    <script src="javascripts/angularApp.js"></script>
    <body ng-controller="mainController">
      <nav class="navbar  " role="navigation">
        <div class="container">

           <div class="navbar-header">
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
              <span class="sr-only">Toggle navigation</span>
              <span class="icon-bar"></span>
              <span class="icon-bar"></span>
              <span class="icon-bar"></span>
            </button>
            <a class="navbar-brand" href="#"></a>
          </div>
          <div id="navbar" class="navbar-collapse collapse">
            <ul class="navbar-nav navbar-right nav">
            <li >
                <a ui-sref="About"> <b>About</b></a>
              </li>
              <li>
                <a ui-sref="Blog"> <b>Blog</b></a>
              </li>
              <li ">
                <a ui-sref="projects"> <b>Projects</b></a>
              </li>
              <li ">
                <a ui-sref="Contact"> <b>Contact</b></a>
              </li>
            </ul>
          </div><!--/.navbar-collapse -->
        </div>
      </nav>

        <div>

<div class="jumbotron">
 <div class="container">
<h1>Site Mangagment <br> Welcome '.$_SESSION['User'].'</h1>
</div>
</div>

<div class="container">
 <div class="row">
   <div class="col-md-8">
     <h3>About Me</h3>
     <form name="Blog" action="newBlog.php" method="post">
       <input type="text" name="Title"placeholder="Title" >
       <button type="submit" class="btn btn-primary">Submit</button>
     </form>
     <iframe src="build/document.html" form="Blog" name="info">
     </iframe>

   </div>

   <div class="container">
     <div class="col-mid-4 ">

     </div>
   </div>
   <hr>
   </div>
</div>





<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
<script src="/javascripts/bootstrap.min.js"></script>

</body>
</html>
';


?>
