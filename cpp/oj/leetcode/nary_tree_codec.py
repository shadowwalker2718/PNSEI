class Node(object):
    def __init__(self, val, children):
        self.val = val
        self.children = children

class Codec:
    def serialize(self, root):
        """Encodes a tree to a single string.
        :type root: Node
        :rtype: str
        """
        if not root:
            return []
        if not root.children:
            return root.val
        return [
            root.val,
            [self.serialize(c) for c in root.children]
        ]
    def deserialize(self, data):
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: Node
        """
        if data == []:
            return None

        # Handle leaf node case when the data is an int instead of list
        if isinstance(data, int):
            return Node(data, [])

        return Node(
            val = data[0],
            children = [self.deserialize(c) for c in data[1]]
        )


# Your Codec object will be instantiated and called as such:
root={"$id":"1","children":[{"$id":"2","children":[{"$id":"5","children":[],"val":5},{"$id":"6","children":[],"val":6}],"val":3},{"$id":"3","children":[],"val":2},{"$id":"4","children":[],"val":4}],"val":1}
codec = Codec()
print codec.deserialize(codec.serialize(root))