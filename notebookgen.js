const fs = require('fs')
const path = require('path')
const spawn = require('child_process').spawn
const through2 = require('through2')
const tmp = require('tmp')
const os = require('os')
const { highlightCpp } = require('./highlight')

const section = ['\\section{', '\\subsection{', '\\subsubsection{']
const extensions = {
  '.cc': 'C++',
  '.cpp': 'C++',
  '.hpp': 'C++',
  '.c': 'C',
  '.java': 'Java',
  '.py': 'Python',
  '.tex': 'Tex',
  '.go': 'Golang'
}

function walk (_path, depth) {
  let ans = ''
  depth = Math.min(depth, section.length - 1)
  fs.readdirSync(_path).sort().forEach(function (file) {
    if (file.startsWith('.')) {
      return // hidden directory
    }
    const f = path.resolve(_path, file)
    const stat = fs.lstatSync(f)
    if (stat.isDirectory()) {
      ans += '\n' + section[depth] + file.replace(/^\d+ - /, '') + '}\n' + walk(f, depth + 1)
    } else if (path.extname(f) in extensions) {
      const title = path.basename(f, path.extname(f)).replace(/^\d+ - /, '')
      ans += '\n' + section[depth] + title + '}\n'
      if (path.extname(f) !== '.tex') {
        const highlighted = highlightCpp(fs.readFileSync(f, 'utf8'))
        ans += '{\\ttfamily\\small\n\\begin{alltt}\n' + highlighted + '\\end{alltt}\n}\n'
      } else {
        ans += fs.readFileSync(f)
      }
    }
  })
  return ans
}

/**
 * pdf must be generated twice in order to generate the table of contents.
 * According to some tests, in windows it must be generated 3 times.
 * */
function genpdf (ans, texPath, tmpobj, iter) {
  const tex = spawn('lualatex', [
    '-interaction=nonstopmode',
    texPath
  ], {
    cwd: tmpobj.name,
    env: process.env,
    stdio: 'inherit' // xả log lualatex realtime ra terminal
  })

  tex.on('error', function (err) {
    console.error(err)
  })

  tex.on('exit', function (code, signal) {
    const outputFile = texPath.split('.')[0] + '.pdf'
    fs.access(outputFile, function (err) {
      if (err) {
        // In đuôi log để biết lỗi LaTeX (thay vì chỉ báo "Not generated")
        try {
          const log = fs.readFileSync(texPath.split('.')[0] + '.log', 'utf8')
            .split('\n').filter(l => l.startsWith('!')).slice(0, 10).join('\n')
          console.error(log || ('Not generated ' + code + ' : ' + signal))
        } catch (e) {
          console.error('Not generated ' + code + ' : ' + signal)
        }
        return
      }
      if (iter === 0) {
        const s = fs.createReadStream(outputFile)
        s.pipe(ans)
        s.on('close', function () {
          tmpobj.removeCallback()
        })
      } else {
        genpdf(ans, texPath, tmpobj, iter - 1)
      }
    })
  })
}

function pdflatex (doc) {
  const tmpobj = tmp.dirSync({ unsafeCleanup: true })
  const texPath = path.join(tmpobj.name, '_notebook.tex')

  const ans = through2()
  ans.readable = true
  const input = fs.createWriteStream(texPath)
  input.end(doc)
  input.on('close', function () {
    const iters = process.platform === 'win32' ? 2 : 1
    genpdf(ans, texPath, tmpobj, iters)
  })

  return ans
}

function normalizeUnixStyle (currentPath) {
  if (os.type() === 'Windows_NT') {
    return currentPath.replace(/\\/g, '/')
  }
  return currentPath
}

function templateParameter (parameter) {
  return `\${${parameter}}`
}

// String.replace chỉ thay thế chỗ đầu tiên; template có ${paper} 2 lần
// nên phải thay toàn cục, nếu không dòng \geometry giữ nguyên chữ ${paper}
function replaceAll (template, parameter, value) {
  return template.split(templateParameter(parameter)).join(value)
}

module.exports = function (_path, options) {
  options.output = options.output || './notebook.pdf'
  options.author = options.author || ''
  options.initials = options.initials || ''

  if (!options.size.endsWith('pt')) options.size += 'pt'
  if (options.image) {
    options.image = normalizeUnixStyle(path.resolve(options.image))
    options.image = '\\centering{\\includegraphics[width=3.5cm]{' + options.image + '}}'
  } else {
    options.image = ''
  }

  let template = fs.readFileSync(path.join(__dirname, 'template_header.tex')).toString()
  template = replaceAll(template, 'author', options.author)
  template = replaceAll(template, 'initials', options.initials)
  template = replaceAll(template, 'fontSize', options.size)
  template = replaceAll(template, 'columns', options.columns)
  template = replaceAll(template, 'paper', options.paper)
  template = replaceAll(template, 'image', options.image)

  template += walk(_path, 0)
  template += '\\end{multicols*}\n'
  template += '\\end{document}'
  pdflatex(template).pipe(fs.createWriteStream(options.output))
}
