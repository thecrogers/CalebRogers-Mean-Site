var mongoose = require('mongoose');

var ProjectSchema = new mongoose.Schema({
  title: String,
  link: String,
  summery: String,
  tags: String,
  content: String,
  hint: String,
  upvotes: {type: Number, default: 0},

});

ProjectSchema.methods.upvote = function(cb) {
  this.upvotes += 1;
  this.save(cb);
};

ProjectSchema.methods.removePost = function(cb) {
  this.where(cb).findOneAndRemove();
};

mongoose.model('Project', ProjectSchema);
