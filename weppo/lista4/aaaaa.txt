function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree.prototype[Symbol.iterator] = function*() {
    const queue = [this];
    while (queue.length) {
        const root = queue.shift();
        if (root.right) queue.push(root.right);
        if (root.left) queue.push(root.left);
        yield root.val;
    }
}

var root = new Tree(1, new Tree(2, new Tree(3)), new Tree(4));
for (var e of root) {
    console.log( e );
}