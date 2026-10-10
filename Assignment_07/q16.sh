cat << 'EOF' > ~/welcome.sh
#!/bin/bash
echo "=========================================="
echo "  Welcome, $USER!"
echo "  Current Date and Time: $(date)"
echo "=========================================="
echo "Contents of your home directory ($HOME):"
ls -la "$HOME"
echo "=========================================="
EOF

