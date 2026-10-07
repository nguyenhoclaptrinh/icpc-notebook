// Minimal C++ syntax highlighter that emits LaTeX suitable for the
// `alltt` environment (only `\`, `{`, `}` are special there, so plain
// UTF-8 text -- e.g. Vietnamese comments -- passes through untouched,
// unlike `listings`/`minted`).

const KEYWORDS = new Set([
  'alignas', 'alignof', 'asm', 'auto', 'bool', 'break', 'case', 'catch',
  'char', 'char8_t', 'char16_t', 'char32_t', 'class', 'concept', 'const',
  'consteval', 'constexpr', 'constinit', 'const_cast', 'continue',
  'co_await', 'co_return', 'co_yield', 'decltype', 'default', 'delete',
  'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit', 'export',
  'extern', 'false', 'float', 'for', 'friend', 'goto', 'if', 'inline',
  'int', 'long', 'mutable', 'namespace', 'new', 'noexcept', 'nullptr',
  'operator', 'private', 'protected', 'public', 'register',
  'reinterpret_cast', 'requires', 'return', 'short', 'signed', 'sizeof',
  'static', 'static_assert', 'static_cast', 'struct', 'switch',
  'template', 'this', 'thread_local', 'throw', 'true', 'try', 'typedef',
  'typeid', 'typename', 'union', 'unsigned', 'using', 'virtual', 'void',
  'volatile', 'wchar_t', 'while'
])

function texEscape (s) {
  let out = ''
  for (const ch of s) {
    if (ch === '\\') out += '\\textbackslash{}'
    else if (ch === '{') out += '\\{'
    else if (ch === '}') out += '\\}'
    else out += ch
  }
  return out
}

function color (name, text) {
  if (text.length === 0) return ''
  return `\\textcolor{${name}}{${text}}`
}

function scanQuoted (line, i, quote) {
  let j = i + 1
  const n = line.length
  while (j < n && line[j] !== quote) {
    j += (line[j] === '\\' && j + 1 < n) ? 2 : 1
  }
  return Math.min(j + 1, n)
}

function highlightLine (line, state) {
  let out = ''
  let i = 0
  const n = line.length

  if (state.inBlockComment) {
    const end = line.indexOf('*/')
    if (end === -1) {
      return color('gray', texEscape(line))
    }
    out += color('gray', texEscape(line.slice(0, end + 2)))
    i = end + 2
    state.inBlockComment = false
  }

  while (i < n) {
    const c = line[i]

    if (c === '/' && line[i + 1] === '/') {
      out += color('gray', texEscape(line.slice(i)))
      break
    }

    if (c === '/' && line[i + 1] === '*') {
      const end = line.indexOf('*/', i + 2)
      if (end === -1) {
        out += color('gray', texEscape(line.slice(i)))
        state.inBlockComment = true
        break
      }
      out += color('gray', texEscape(line.slice(i, end + 2)))
      i = end + 2
      continue
    }

    if (c === '"' || c === "'") {
      const j = scanQuoted(line, i, c)
      out += color('codestring', texEscape(line.slice(i, j)))
      i = j
      continue
    }

    if (/[A-Za-z_]/.test(c)) {
      let j = i + 1
      while (j < n && /[A-Za-z0-9_]/.test(line[j])) j++
      const word = line.slice(i, j)
      out += KEYWORDS.has(word)
        ? `\\textcolor{blue}{\\textbf{${word}}}`
        : texEscape(word)
      i = j
      continue
    }

    let j = i + 1
    while (j < n) {
      const d = line[j]
      if ((d === '/' && (line[j + 1] === '/' || line[j + 1] === '*')) ||
          d === '"' || d === "'" || /[A-Za-z_]/.test(d)) break
      j++
    }
    out += texEscape(line.slice(i, j))
    i = j
  }

  return out
}

function highlightCpp (text) {
  const state = { inBlockComment: false }
  return text.split('\n').map(l => highlightLine(l, state)).join('\n')
}

module.exports = { highlightCpp }
