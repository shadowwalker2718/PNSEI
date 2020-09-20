package binary_search

import (
	"github.com/stretchr/testify/assert"
	"sort"
	"testing"
)

func Test_sample(t *testing.T) {
	a := []int{1, 3, 6, 10, 15, 21, 28, 36, 45, 55}

	x := 6
	i := sort.Search(len(a), func(i int) bool { return a[i] >= x })
	assert.True(t, len(a)>i)

	x = 5
	assert.True(t, 2==sort.Search(len(a), func(i int) bool { return a[i] >= x }))

	x = 500
	assert.True(t, len(a)==sort.Search(len(a), func(i int) bool { return a[i] >= x }))
}
