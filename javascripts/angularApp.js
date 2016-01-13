angular.module('portfolio', ['ui.router','angularUtils.directives.dirPagination'])
.config([
  '$stateProvider',
  '$urlRouterProvider',
  function($stateProvider, $urlRouterProvider) {

  $urlRouterProvider.otherwise('/about');

  $stateProvider
  .state('default', {
    url: "/default",
    templateUrl: "pages/landing.html",
    controller: "mainController"

  })
  .state('About', {
    url: "/about",
    templateUrl: "pages/index.html",
    controller: "mainController"

  })
  .state('Blog', {

    url: "/blog",
    templateUrl: "pages/Blog.html",
    controller: "mainController",
    resolve: {
    postPromise: ['posts', function(posts){

    return posts.getAll();
    }]
    }

  })
  .state('projects', {

    url: "/projects",
    templateUrl: "pages/projects.html",
    controller: "mainController",
    resolve: {

    postPromise: ['projects', function(projects){

        return projects.getAllProjects();
      }]
    }

  })

  .state('project', {
    url: '/projects/{id}',
    templateUrl: 'pages/code.html',
    controller: 'ProjectCtrl'
  })

  .state('Contact', {
    url: "/contct",
    templateUrl: "pages/contact.html",
    controller: "mainController"

  })
  .state('Tecm ', {
    url: "/Tecm",
    templateUrl: "pages/Tecm.ejs",
    controller: "mainController"

  })
  .state('manage', {
    url: "/manage",
    templateUrl: "pages/manage.html",
    controller: "mainController",
    resolve: {
      postPromise: ['posts','projects', function(posts,projects){

        return posts.getAll(), projects.getAllProjects();
      }]
    }
})

  .state('post', {
    url: '/posts/{id}',
    templateUrl: 'pages/posts.ejs',
    controller: 'PostsCtrl'
  });
}])

.controller('mainController', [
'$scope','$log','posts','projects',
function($scope,$log,posts,projects){
  $scope.test = 'Hello world!';
  $scope.posts=posts.posts;
  $scope.projects=projects.projects;

$scope.addPost = function(){
  if(!$scope.title || $scope.title === '') { return; }
  var d = new Date();
  var fulldate=d.getDay()+","+d.getDate()+" "+d.getFullYear();

  posts.create({
    title: $scope.title,
    tags: $scope.tags,
    summery: $scope.summery,
    content: $scope.content,
    link: $scope.link,
    date: fulldate,
  });
  $scope.title = '';
  $scope.link = '';
  $scope.tags = '';
  $scope.summery = '';
  $scope.content='';
  $scope.fulldate='';
};

$scope.addProject = function(){
  if(!$scope.proTitle || $scope.proTitle === '') { return; }

  projects.create({
    title: $scope.proTitle,
    tags: $scope.proTags,
    summery: $scope.proSummery,
    content: $scope.proContent,
    link: $scope.proLink,
    hint: $scope.proHint,
  });

  $scope.proTitle = '';
  $scope.proTags = '';
  $scope.proSummery = '';
  $scope.proContent = '';
  $scope.proLink='';
  $scope.proHint='';
};



$scope.getLink=function(post)
{
  return +post;
};

$scope.removePost=function(post)
{
  posts.removePost(post);
};

$scope.removeProject=function(project)
{
  projects.removeProject(project);
};

$scope.incrementUpvotes = function(post) {
  posts.upvote(post);
};

$scope.incrementUpvotesProject = function(project) {
  projects.upvoteProject(project).$apply();
};

$scope.numPages = function(index){
  return math.floor(index/3);
};

$scope.setPage = function (pageNo) {
  $scope.currentPage = pageNo;
};
$scope.result="Code has not run yet.";

$scope.pageChanged = function() {
  $log.log('Page changed to: ' + $scope.currentPage);
};
$scope.results =projects.results;

$scope.maxSize = 3;

$scope.bigTotalItems = 4;
$scope.bigCurrentPage = 1;


}])

.controller('PostsCtrl', [
'$scope',
'$stateParams',
'posts',
function($scope, $stateParams, posts){

  $scope.post = posts.posts[$stateParams.id];

}])

.controller('ProjectCtrl', [
'$scope',
'$stateParams',
'projects',
function($scope, $stateParams, projects){
  $scope.project=projects.Project($stateParams.id,projects);
  $scope.result="Code has not run yet.";
  $scope.runCode=function()
  {
    $scope.result=projects.run($stateParams.id,$scope.args);
  };
}])


.factory('posts', ['$http', function($http){//,'projects'
  var o = {
    posts: [{title: "",tags: "",summer:"",link:"",content:""}],
    //projects:[{title: "",tags: "",backend:"",link:"",content:""}]
  };

   o.create = function(post) {
    return $http.post('/posts', post).success(function(data){
     o.posts.push(data);
    });
   };

   o.getAll = function(name,args) {
    return $http.get('/posts').success(function(data){
      angular.copy(data, o.posts);
      o.posts.getLast(o.posts);
    });
  };

  o.getAllProjects = function() {
    return $http.get('/projects').success(function(data){
      angular.copy(data, o.projects);
    });
  };

  o.Post = function(post) {
    return $http.get('/posts/' + post._id);

    };

    o.removePost=function(post){
      return $http.put('posts/'+post._id +'/remove')
      .sucess(function(data){
        post.title='';
      });
    };

  o.upvote = function(post) {
    return $http.put('/posts/' + post._id + '/upvote')
    .success(function(data){
      post.upvotes += 1;
    });
  };
return o;

}])

.factory('projects', ['$http', function($http){//,'projects'
var l = {

  projects:[{Title: "",tags: "",Help:"",ID:"",NumInp:"",SRC:"",path:"",Desc:"",link:"",upvotes:""}],
  result:""
};

l.create = function(project) {
  return $http.post('/projects', project).success(function(data){
    l.projects.push(data);
  });
};

l.getAll = function() {
  return $http.get('/projects.php').success(function(data){
    angular.copy(data, l.projects);
    l.projects.getLast(l.projects);
  });
};

l.getAllProjects = function() {
  return $http.get('/projects.php?action=all').success(function(data){
    angular.copy(data, l.projects);
  });
};

l.Project = function(id, projects) {

  for(var i = 0; i < projects.projects.length; i++)
  {
    if(projects.projects[i].ID == id)
    {
      return projects.projects[i];
    }
  }
};

l.run=function(name,args){
  return $http.get('/Run.php?&ID='+name+'&args='+args).success(function(data){
    l.result.push(data);
  });

};


l.removeProject=function(project){
  return $http.get('projects.php?action=remove&ID='+project._id )
  .sucess(function(data){
    project.title='';
  });
};

l.upvoteProject = function(project) {

  return $http.get('/projects.php?action=upvote&ID='+ project.ID )
  .success(function(data){
    project.upvotes += 1;
  });

};

return l;

}]);
