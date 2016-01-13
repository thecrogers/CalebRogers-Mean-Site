var mongoose = require('mongoose');

var PostSchema = new mongoose.Schema({
  title: String,
  link: String,
  summery: String,
  tags: String,
  content: String,
  date: String,
  upvotes: {type: Number, default: 0},
  comments: [{ type: mongoose.Schema.Types.ObjectId, ref: 'Comment' }]
});

PostSchema.methods.upvote = function(cb) {
  this.upvotes += 1;
  this.save(cb);
};

PostSchema.methods.removePost = function(cb) {
  this.where(cb).findOneAndRemove();
};
mongoose.model('Post', PostSchema);
