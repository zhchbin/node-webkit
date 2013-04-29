var gui = require('nw.gui');
var assert = require('assert');
require('should');

describe('HotKey', function(){
  describe('.key', function(){
    it('should be undefined if no key specified.', function(){
      var hotKey;
      try {
        hotKey = new gui.HotKey();
      } catch (err) {}
      assert.equal(hotKey, undefined);

      try {
        hotKey = new gui.HotKey({"keydown": function() {}});
      } catch (err) {}

      assert.equal(hotKey, undefined);
    });

    it('should be an object if key specified.', function() {
      try {
        hotKey = new gui.HotKey({"key": "Alt+Shift+S"});
      } catch (err) {}

      hotKey.should.be.a('object');
      assert.equal(hotKey.key, "Alt+Shift+S");
    });
  });

  describe('.keydown', function() {
    it('should be undefined if keydown is not an function object.', function() {
      var hotKey;
      try {
        hotKey = new gui.HotKey({key: 'Alt+Shift+S', keydown: "foo"});
      } catch(err) {}

      assert.equal(hotKey, undefined);
    });

    it('should be an object if keydown key and keydown specified.', function() {
      var keydownfun = function() {};
      var hotKey = new gui.HotKey({key: 'Alt+Shift+S', keydown: keydownfun});

      hotKey.should.be.a('object');
      assert.equal(hotKey.keydown, keydownfun);
    });
  });

  describe('.keyup', function() {
    it('should be undefined if keyup is not an function object.', function() {
      var hotKey;
      try {
        hotKey = new gui.HotKey({key: 'Alt+Shift+S', keyup: "foo"});
      } catch(err) {}

      assert.equal(hotKey, undefined);
    });

    it('should be an object if keydown key and keyuo specified.', function() {
      var keyupfun = function() {};
      var hotKey = new gui.HotKey({key: 'Alt+Shift+S', keyup: keyupfun});

      hotKey.should.be.a('object');
      assert.equal(hotKey.keyup, keyupfun);
    });
  });
});

describe('App.registerGlobalHotKey', function() {
  it('should register failed if the parameter is not an HotKey object.', function(done) {
    var object = new Object();
    try {
      gui.App.registerGlobalHotKey(object);
    } catch(err) {
      done();
    }
  });

  it('should register failed if the same key has been registered.', function(done) {
    var hotKey = new gui.HotKey({key: "Alt+Shift+S"});
    hotKey.failed = function(msg) {
      assert.equal(msg, "Register global hot key failed, maybe it has been registered.");
      done();
    };
    gui.App.registerGlobalHotKey(hotKey);
    gui.App.registerGlobalHotKey(hotKey);
  });

  it('should register failed for invalid key.', function(done) {
    var hotKey = new gui.HotKey({key: "foo"});
    hotKey.failed = function(msg) {
      assert.equal(msg, "Invalid value for 'hotkey[0] on windows': FOO.");
      done();
    }
    gui.App.registerGlobalHotKey(hotKey);
  });
});

describe('App.unregisterGlobalHotKey', function() {
  it('should unregister failed if the parameter is not an HotKey object.', function(done) {
    var object = new Object();
    try {
      gui.App.unregisterGlobalHotKey(object);
    } catch(err) {
      done();
    }
  });
});
