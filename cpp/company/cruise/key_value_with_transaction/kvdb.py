# https://github.com/zackdever/vsims

''' https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=438210&highlight=cruise
2018(7-9月) 码农类General 硕士 全职@cruise - 猎头 - Onsite  | Other | 在职跳槽
报几个地里没有的面经,
Implement a key value store with transactions and rollbacks

类似这个
https://github.com/zackdever/vsims. From 1point 3acres bbs

设计一个类似lyft的,但是用无人车的手机app
'''


"""A very simple in-memory key-value store.
db = vsims.DB() -> a new empty database.
db.set('a', 10) -> set a to 10
db.get('a') - > get the value of a
Also supports transactional blocks.
Built for: http://www.thumbtack.com/challenges
More: https://github.com/zever/vsims

Our database supports nested transactional blocks as you can tell by the above commands. Remember,
ROLLBACK only rolls back the most recent transaction block, while COMMIT closes all open
transactional blocks. Any command issued outside of a transactional block commits automatically.
"""
import sys


class Block:
    """A block of operations that can be called in reverse order.
    Use: To isolate a block of commands, before executing each command,
    log a command which will reverse it.
    Then if needed, simply rollback to undo that block.
    """

    def __init__(self):
        self.ops = []

    def log(self, command, *args):
        """Adds the command and arguments to the log.
        command - a function that will be called on rollback
        args - arguments to be supplied to the command on rollback
        """
        self.ops.append((command, args))

    def rollback(self):
        """Call all the logged commands in reverse order."""
        for op in reversed(self.ops):
            op[0](*op[1])


class NestedStore:
    """Simple key-value store that supports nested transactional blocks."""

    def __init__(self):
        self.blocks = []
        self.store = {}
        self.value_counts = {}

    def set(self, key, value, doLog=True):
        """Add the key to the store if not already present, and set its value.
        key - key to add or update
        value - value set for key
        doLog - determines if a reverse operation should be logged
        """
        has_key = self.has_key(key)

        if not self.is_flat() and doLog:
            block = self.blocks[-1]
            if has_key:
                block.log(self.set, key, self.get(key), False)
            else:
                block.log(self.delete, key, False)

        if has_key:
            old_value = self.get(key)
            if old_value != value:
                self._update_value_count_(old_value, -1)
                self._update_value_count_(value, 1)
        else:
            self._update_value_count_(value, 1)

        self.store[key] = value

    def get(self, key):
        """Returns the value of the given key.
        throws: KeyError if key is not present in the store
        """
        return self.store[key]

    def has_key(self, key):
        """Determines if the store contains the key."""
        return self.store.has_key(key)

    def delete(self, key, doLog=True):
        """Deletes the key from the store if present.
        key - key to delete
        doLog - determines if a reverse operation should be logged
        """
        if self.has_key(key):
            if not self.is_flat() and doLog:
                self.blocks[-1].log(self.set, key, self.get(key), False)

            self._update_value_count_(self.get(key), -1)
            del self.store[key]

    def nest(self):
        """Start a new transactional block."""
        self.blocks.append(Block())

    def pop_nest(self):
        """End the currently open transactional block.
        throws: IndexError if there are no open transactional blocks.
        """
        self.blocks.pop().rollback()

    def flatten(self):
        """Permanently stores and closes all open transactional blocks."""
        self.blocks = []

    def is_flat(self):
        """Returns True if there are no open transactional blocks."""
        return len(self.blocks) == 0

    def numequalto(self, value):
        """Returns the number of keys set to the provided value."""
        if not self.value_counts.has_key(value):
            self.value_counts[value] = 0
            return 0

        return self.value_counts[value]

    def _update_value_count_(self, value, count):
        """Set or update the count for the provided value."""
        if self.value_counts.has_key(value):
            self.value_counts[value] += count
        else:
            self.value_counts[value] = count


class DB:
    """A simple in-memory key-value store with nested transactional blocks."""

    # Commands are implicity mapped to methods of the same name, but lowercased.
    _commands_ = ['SET', 'GET', 'UNSET', 'NUMEQUALTO', 'BEGIN', 'ROLLBACK', 'COMMIT', 'END']

    def __init__(self):
        self._store_ = NestedStore()

    def run(self, query):
        """Runs the provided query and returns the result."""
        tokens = query.split(' ')
        command, args = tokens[0], (self._parse_token_(token) for token in tokens[1:])

        if command in DB._commands_:
            try:
                return DB.__dict__[command.lower()](self, *args)
            except TypeError:
                return '[ERROR] Probably incorrect arguments for command: {}'.format(command)
        else:
            return '[ERROR] Unrecognized command: {}'.format(command)

    def set(self, key, value):
        """SET [name] [value]: Set a variable [name] to the value [value].
        Neither variable names or values will ever contain spaces.
        """
        self._store_.set(key, value)

    def get(self, key):
        """GET [name]: Print out the value stored under the variable [name].
        Print NULL if that variable name hasn't been set.
        """
        return self._store_.get(key) if self._store_.has_key(key) else 'NULL'

    def unset(self, key):
        """UNSET [name]: Unset the variable [name]."""
        self._store_.delete(key)

    def numequalto(self, value):
        """NUMEQUALTO [value]: Return the number of variables equal to [value].
        If no values are equal, this should output 0.
        """
        return self._store_.numequalto(value)

    def begin(self):
        """BEGIN: Open a transactional block."""
        self._store_.nest()

    def rollback(self):
        """ROLLBACK: Rollback all of the commands from the most recent transaction block.
        If no transactional block is open, print out INVALID ROLLBACK.
        """
        if self._store_.is_flat():
            return 'INVALID ROLLBACK'
        else:
            self._store_.pop_nest()

    def commit(self):
        """COMMIT: Closes all open transactional blocks."""
        self._store_.flatten()

    def end(self):
        """END: Exit the program."""
        sys.exit()

    def _parse_token_(self, token):
        """Converts the token into an int or float if applicable.
        token - the string to parse
        Returns the token as is, or as an int or float if possible.
        """
        try:
            return int(token)
        except ValueError:
            try:
                return float(token)
            except ValueError:
                return token


def shell():
    """A very simple shell."""
    db = DB()

    while True:
        query = sys.stdin.readline().strip()
        if query != None:
            result = db.run(query)
            if result != None:
                print result


if __name__ == '__main__':
    shell()
