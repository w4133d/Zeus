# Zeus

**If you find use in this, it would be great if you would credit Scob, or if you want to support him even more, [Donate](https://www.paypal.me/scobalula). These tools take a ton of time to make and he could easily keep them to himself or charge for them.**

This is a tool that will allow you to convert bsp files produced by Black Ops III's cod2map64 to obj or xmodel_export. These can then be opened in Maya, etc. for creating xcams, etc. or put straight back into APE to reuse in any way you want.

# Using Zeus

**This tool is primarily provided for Black Ops 3 mappers looking to create cinematics, converting large parts of their maps to models, etc. If you're looking for the tool to do something more, then it's not for you.**

To download Zeus, [Click Here](https://github.com/w4133d/Zeus/releases).

Using Zeus is quite simple. Drag any `.map` file (including prefabs) or `.d3dbsp` file (compiled maps found in `<BO3 Root>\share\raw\maps\**`) onto `Zeus.exe` & watch the magic happen.

Please note your map file needs at least 1 brush (can be caulk) for the compiler to process it.

Finally, once you bring your model into APE, it is recommended to tick "Preserve original UVs", this allows the UVs to be stored with higher precision that is required due to the large UV coordinates used by map geo.

In the future some further options for filtering geo, or exporting directly to `.xmodel_bin`, etc. will be provided.

Note:
I forked Zeus & added the ability for it to auto-convert the `.d3dbsp` file when you drag on a `.map`

\- prov3ntus

# License/Disclaimer

Zeus was mostly made to suit my needs and it does what I want to do, however, I am open to suggestions or feature requests within reason.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
