var mongoose = require('mongoose');
var Post = mongoose.model('Post');
var Project = mongoose.model('Project');
var Comment = mongoose.model('Comment');
var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});

module.exports = router;

router.get('/posts', function(req, res, next) {
  Post.find(function(err, posts){
    if(err){ return next(err); }

    res.json(posts);
  });
});

router.post('/posts', function(req, res, next) {
  var post = new Post(req.body);

  post.save(function(err, post){
    if(err){ return next(err); }

    res.json(post);
  });
});

router.param('post', function(req, res, next, id) {
  var query = Post.findById(id);

  query.exec(function (err, post){
    if (err) { return next(err); }
    if (!post) { return next(new Error("can't find post")); }

    req.post = post;
    return next();
  });
});

router.get('/posts/:post', function(req, res) {
  res.json(req.post);
});


router.put('/posts/:post/upvote', function(req, res, next) {
  req.post.upvote(function(err, post){
    if (err) { return next(err); }

    res.json(post);
  });
});

router.put('/posts/:post/remove', function(req, res, next) {
  req.post.removePost(function(err, post){
    if (err) { return next(err); }

    res.json(post);
  });
});


//space



router.get('/projects', function(req, res, next) {
  Project.find(function(err, projects){
    if(err){ return next(err); }

    res.json(projects);
  });
});

router.post('/projects', function(req, res, next) {
  var project = new Project(req.body);

  project.save(function(err, project){
    if(err){ return next(err); }

    res.json(project);
  });
});

router.put('/projects/code/', function(req, res, next) {
  var file=req.query.file;
  var args=req.query.args;
  console.log(file);
  console.log(args);
  var output=child_process.execFile("code/"+file,args,function(error, stdout, stderr){
      res.json(stdout);
      console.log(stdout);
    });
});

router.param('project', function(req, res, next, id) {
  var query = Project.findById(id);

  query.exec(function (err, project){
    if (err) { return next(err); }
    if (!project) { return next(new Error("can't find project")); }

    req.project = project;
    return next();
  });
});

router.get('/projects/:project', function(req, res) {
  res.json(req.project);
});


router.put('/projects/:project/upvote', function(req, res, next) {
  req.project.upvote(function(err, project){
    if (err) { return next(err); }

    res.json(project);
  });
});


router.put('/projects/:project/remove', function(req, res, next) {
  req.project.removeProject(function(err, project){
    if (err) { return next(err); }

    res.json(project);
  });
});
